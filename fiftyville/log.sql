-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema
SELECT * FROM crime_scene_reports;
--crime number 295 Humphrey Street Bakery 3 witness. 28 july 2023 10.15 am
SELECT * FROM interviews WHERE month=7 AND day = 28;
--witness Ruth Eugene Raymond Eugene recognizes thief
--earliest flioght the next day eugene recognizes thief drove in a car atm on Leggett street
SELECT * FROM atm_transactions WHERE month=7 AND day=28 AND atm_location LIKE 'Leggett%';
SELECT * FROM phone_calls WHERE duration<60 AND day=28 AND month=7;

SELECT phone_number, license_plate FROM people JOIN bank_accounts WHERE bank_accounts.person_id= people.id AND account_number IN (SELECT account_number FROM atm_transactions WHERE month=7 AND day=28 AND atm_location LIKE 'Leggett%');

SELECT caller FROM phone_calls WHERE duration<60 AND day=28 AND month=7 INTERSECT SELECT phone_number FROM people JOIN bank_accounts WHERE bank_accounts.person_id= peopl
e.id AND account_number IN (SELECT account_number FROM atm_transactions WHERE month=7 AND day=28 AND atm_location LIKE 'Leggett%');
--suspected phone numbers (286) 555-6063 >> 1106N58,(338) 555-6650 >>8X428L0,(367) 555-5533>>94KL13X,(770) 555-1861>>322W7JE,(826) 555-1652>>30G67EN

SELECT * FROM bakery_security_logs WHERE day=28 AND month=7 AND hour=10 AND minute<25 AND minute >15;
--remaining suspects license plate and phone nos 94KL13X>>(367) 555-5533, 322W7JE>>(770) 555-1861

SELECT * FROM airports WHERE city = 'Fiftyville';
--airport id 8

SELECT * FROM flights WHERE origin_airport_id = 8 AND day = 29 AND month=7 ORDER BY hour ASC, minute ASC;
--destination airport id 4
--Thief escaped to New York city
SELECT * FROM passengers JOIN people WHERE passengers.passport_number=people.passport_number AND (phone_number= '(367) 555-5533' OR '(770) 555-1861');
--culprit is Bruce phone number (367) 555-5533
--phone number of accomplice is (375) 555-8161
SELECT * FROM people WHERE phone_number='(375) 555-8161';
--accomplice is Robin
