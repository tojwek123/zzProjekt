use trackDay

INSERT INTO userTypes VALUES ('Racer');
INSERT INTO userTypes VALUES ('Referee');
INSERT INTO userTypes VALUES ('Administrator');

INSERT INTO users
SELECT id, 'Zdzisek', NULL, NULL, 'ec7117851c0e5dbaad4effdb7cd17c050cea88cb'
FROM userTypes WHERE type = 'Racer';

INSERT INTO users
SELECT id, 'TigerBonzo', 'Franek', 'Kimono', 'ec7117851c0e5dbaad4effdb7cd17c050cea88cb'
FROM userTypes WHERE type = 'Racer';

INSERT INTO users
SELECT id, 'Bolo', 'ec7117851c0e5dbaad4effdb7cd17c050cea88cb'
FROM userTypes WHERE type = 'Referee';

INSERT INTO cars VALUES ('Mercedes', 'SLS');
INSERT INTO cars VALUES ('Ford', 'Focus RS');

INSERT INTO laps
SELECT id, '00:00:45.123', '2018-05-17 10:33:12', (SELECT id FROM cars WHERE brand = 'Mercedes' and model = 'SLS')
FROM users WHERE name = 'Zdzisek'

INSERT INTO laps
SELECT id, '00:00:41.123', '2018-05-17 10:34:12', (SELECT id FROM cars WHERE brand = 'Ford' and model = 'Focus RS')
FROM users WHERE name = 'Zdzisek'
  
INSERT INTO laps
SELECT id, '00:00:46.5', '2018-05-17 10:55:12', (SELECT id FROM cars WHERE brand = 'Ford' and model = 'Focus RS')
FROM users WHERE name = 'Zdzisek'

INSERT INTO laps
SELECT id, '00:00:42.5', '2018-05-17 10:55:12', (SELECT id FROM cars WHERE brand = 'Mercedes' and model = 'SLS')
FROM users WHERE name = 'TigerBonzo'

INSERT INTO availableDates VALUES ('2018-06-23 10:00:00')
INSERT INTO availableDates VALUES ('2018-06-24 11:00:00')
INSERT INTO availableDates VALUES ('2018-06-26 12:00:00')
INSERT INTO availableDates VALUES ('2018-06-26 13:00:00')

INSERT INTO reservedLaps VALUES (2, 1, 1)
INSERT INTO reservedLaps VALUES (2, 2, 2)