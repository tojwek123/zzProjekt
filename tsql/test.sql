USE trackDay

INSERT INTO laps
SELECT id, '00:00:15.5', '2018-06-17 10:55:12', (SELECT id FROM cars WHERE brand = 'Ford' and model = 'Focus RS')
FROM users WHERE name = 'Zdzisek'

--EXEC getReservedLapsPretty 1

--SELECT * FROM reservedLaps


--SELECT *--DISTINCT cars.id, cars.brand, cars.model
--FROM cars 
--LEFT JOIN reservedLaps ON reservedLaps.carId = cars.id
--LEFT JOIN availableDates ON availableDates.id = reservedLaps.dateId
--WHERE 

--INSERT INTO reservedLaps VALUES (2, 1, 2)


--;WITH reservedCars AS 
--( 
--	SELECT cars.*
--	FROM cars
--	LEFT JOIN reservedLaps ON reservedLaps.carId = cars.id
--	WHERE reservedLaps.dateId = 3
--) 
--SELECT cars.* FROM reservedCars
--RIGHT JOIN cars on cars.id = reservedCars.id
--WHERE reservedCars.id IS NULL

