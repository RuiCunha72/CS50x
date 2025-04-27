-- Keep a log of any SQL queries you execute as you solve the mystery.


-- To see all the scene_reports on the day of the theft and cross the information needed.
SELECT * 
    FROM crime_scene_reports 
    WHERE year = 2024 
    AND month = 7 
    AND day = 28;     
-- 295|2024|7|28|Humphrey Street|Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today 
-- with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.


-- To see all the interviews done regarding the scene of the theft.
SELECT * 
    FROM interviews 
    WHERE year = 2024 
    AND month = 7 
    AND day = 28; 
-- 161|Ruth|2024|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. 
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- 162|Eugene|2024|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- 163|Raymond|2024|7|28|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, 
-- I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the
-- other end of the phone to purchase the flight ticket.



-- To check all the license plates who exited the parking lot in a time fram of 10min.
SELECT * 
    FROM bakery_security_logs 
    WHERE year = 2024 
    AND month = 7 
    AND day = 28 
    AND hour = 10
    AND minute >= 5 
    AND minute <= 25;
-- 260|2024|7|28|10|16|exit|5P2BI95
-- 261|2024|7|28|10|18|exit|94KL13X
-- 262|2024|7|28|10|18|exit|6P58WS2
-- 263|2024|7|28|10|19|exit|4328GD8
-- 264|2024|7|28|10|20|exit|G412CB7
-- 265|2024|7|28|10|21|exit|L93JTIZ
-- 266|2024|7|28|10|23|exit|322W7JE
-- 267|2024|7|28|10|23|exit|0NTHK55




 -- To see all the withdraws made on Legget Street on the day of the theft.
SELECT * 
    FROM atm_transactions 
    WHERE year = 2024 
    AND month = 7 
    AND day = 28 
    AND atm_location = 'Leggett Street';
-- 246|28500762|2024|7|28|Leggett Street|withdraw|48
-- 264|28296815|2024|7|28|Leggett Street|withdraw|20
-- 266|76054385|2024|7|28|Leggett Street|withdraw|60
-- 267|49610011|2024|7|28|Leggett Street|withdraw|50
-- 269|16153065|2024|7|28|Leggett Street|withdraw|80
-- 288|25506511|2024|7|28|Leggett Street|withdraw|20
-- 313|81061156|2024|7|28|Leggett Street|withdraw|30
-- 336|26013199|2024|7|28|Leggett Street|withdraw|35



-- To see all the phone calls made with less than 1min on the day of the theft.
SELECT * 
    FROM phone_calls 
    WHERE year = 2024 
    AND month = 7 
    AND day = 28 
    AND duration < 60; 
-- 221|(130) 555-0289|(996) 555-8899|2024|7|28|51
-- 224|(499) 555-9472|(892) 555-8872|2024|7|28|36
-- 233|(367) 555-5533|(375) 555-8161|2024|7|28|45
-- 251|(499) 555-9472|(717) 555-1342|2024|7|28|50
-- 254|(286) 555-6063|(676) 555-6554|2024|7|28|43
-- 255|(770) 555-1861|(725) 555-3243|2024|7|28|49
-- 261|(031) 555-6622|(910) 555-3251|2024|7|28|38
-- 279|(826) 555-1652|(066) 555-9701|2024|7|28|55
-- 281|(338) 555-6650|(704) 555-2131|2024|7|28|54



-- To get the first flight leaving Fiftyville the next day after the theft.
SELECT * 
    FROM flights 
    WHERE year = 2024 
    AND month = 7 
    AND day = 29 
    AND origin_airport_id = 
        (SELECT id FROM airports WHERE city = 'Fiftyville') 
    ORDER BY hour, minute LIMIT 1;
-- 36|8|4|2024|7|29|8|20



-- To get the destination airport of the flight the thiefs got.
SELECT * 
    FROM airports 
    WHERE id = 4;
-- 4|LGA|LaGuardia Airport|New York City



-- To get all the passengers passport in the fligth they used.
SELECT passport_number 
    FROM passengers 
    WHERE flight_id = 36;
-- 7214083635
-- 1695452385
-- 5773159633
-- 1540955065
-- 8294398571
-- 1988161715
-- 9878712108
-- 8496433585



-- To get all the names, phone number and license_plate from the passengers who were in the flight
SELECT name, phone_number, license_plate 
    FROM people 
    WHERE passport_number IN 
        (SELECT passport_number 
        FROM passengers 
        WHERE flight_id = 36);
-- Kenny|(826) 555-1652|30G67EN
-- Sofia|(130) 555-0289|G412CB7
-- Taylor|(286) 555-6063|1106N58
-- Luca|(389) 555-5198|4328GD8
-- Kelsey|(499) 555-9472|0NTHK55
-- Edward|(328) 555-1152|130LD9Z
-- Bruce|(367) 555-5533|94KL13X
-- Doris|(066) 555-9701|M51FA04


-- To return all the people who are in the plane, had a phone call, being the caller, with duration less than 1 min, had their license plate
-- on the the bakery security logs and made a withdrwall on the Leggett Street atm in the day of the theft
SELECT name 
    FROM people 
    JOIN bank_accounts
    ON people.id = bank_accounts.person_id
    WHERE people.phone_number IN 
        (SELECT caller 
            FROM phone_calls
            WHERE year = 2024 
            AND month = 7 
            AND day = 28 
            AND duration < 60)
    AND people.passport_number IN
        (SELECT passport_number
            FROM passengers
            WHERE flight_id = 36)
    AND people.license_plate IN
        (SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2024 
            AND month = 7 
            AND day = 28
            AND hour = 10
            AND minute >= 5 
            AND minute <= 25)
    AND bank_accounts.account_number IN
        (SELECT account_number
            FROM atm_transactions 
            WHERE year = 2024 
            AND month = 7 
            AND day = 28 
            AND transaction_type = 'withdraw'
            AND atm_location = 'Leggett Street');
-- Bruce



-- Now that we already know the thief is Bruce and he is the caller, we just need to check who was in a call with him that day
SELECT name
    FROM people
    WHERE phone_number IN
        (SELECT receiver 
            FROM phone_calls
            WHERE caller = 
                (SELECT phone_number
                FROM people
                WHERE name = 'Bruce')
            AND year = 2024 
            AND month = 7 
            AND day = 28 
            AND duration < 60);
-- Robin