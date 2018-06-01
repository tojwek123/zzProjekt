USE trackDay

DELETE FROM reservedLaps WHERE id = 1

SELECT * FROM reservedLaps

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

