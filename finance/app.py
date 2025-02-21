import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    if user_id:
        rows = db.execute("SELECT symbol, shares FROM portfolio WHERE user_id = ?", user_id)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        total_value = cash
        holdings = []
        for row in rows:
            stock = lookup(row["symbol"])
            total_value += row["shares"] * stock["price"]
            holdings.append({
                "symbol": row["symbol"],
                "shares": row["shares"],
                "price": stock["price"],
                "total": row["shares"] * stock["price"]
            })
        return render_template("index.html", holdings=holdings, total_value=total_value, cash=cash)

    return apology("NO ACCOUNT LOGGED IN!")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]
        symbol = request.form.get("symbol")
        number = request.form.get("shares")

        if not symbol or not number:
            return apology("Must provide symbol and number of shares")

        try:
            number = int(number)
        except ValueError:
            return apology("Number of shares must be an integer")
        if number <= 0:
            return apology("Number of shares must be a positive integer")

        stock = lookup(symbol)
        if not stock:
            return apology("Enter valid symbol")

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        price = stock["price"]
        total_cost = price * number

        if total_cost > cash:
            return apology("You don't have enough cash!")

        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)
        existing_shares = db.execute("SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?", user_id, symbol)
        if existing_shares:
            db.execute("UPDATE portfolio SET shares = shares + ? WHERE user_id = ? AND symbol = ?", number, user_id, symbol)
        else:
            db.execute("INSERT INTO portfolio (user_id, symbol, shares) VALUES (?, ?, ?)", user_id, symbol, number)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", user_id, symbol, number, price)
        latest_transaction = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY transacted DESC LIMIT 1", user_id)
        return render_template("buy.html", latest_transaction=latest_transaction[0])
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        if stock:
            return render_template("quoted.html", stock=stock)
        else:
            return apology("Invalid symbol")
    else:
        return render_template("quote.html")




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        passwordag = request.form.get("confirmation")

        if not username or not password or not passwordag:
            return apology("must provide username and password")

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) > 0:
            return apology("username already exists")

        if password == passwordag:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
            return redirect("/")
        else:
            return apology("Passwords do not match!")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        number = int(request.form.get("number"))

        if number <= 0:
            return apology("Number of shares must be a positive integer.")

        stock = lookup(symbol)
        shares = db.execute("SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?", user_id, symbol)

        if not shares:
            return apology("You don't own any shares of this stock.")

        shares = shares[0]["shares"]

        if stock:
            price = stock["price"]
        else:
            return apology("Enter valid symbol.")

        total_cost = price * number

        if shares < number:
            return apology("You don't have enough shares!")

        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_cost, user_id)

        if shares == number:
            db.execute("DELETE FROM portfolio WHERE user_id = ? AND symbol = ?", user_id, symbol)
        else:
            db.execute("UPDATE portfolio SET shares = shares - ? WHERE user_id = ? AND symbol = ?", number, user_id, symbol)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", user_id, symbol, -number, price)
        latest_transaction = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY transacted DESC LIMIT 1", user_id)
        return render_template("sell.html", latest_transaction=latest_transaction[0])
    else:
        return render_template("sell.html")
