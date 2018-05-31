CREATE PROCEDURE getAvailableCars @dateId DATETIME
AS
;WITH reservedCars AS 
( 
	SELECT cars.*
	FROM cars
	LEFT JOIN reservedLaps ON reservedLaps.carId = cars.id
	WHERE reservedLaps.dateId = @dateId
) 
SELECT cars.* FROM reservedCars
RIGHT JOIN cars on cars.id = reservedCars.id
WHERE reservedCars.id IS NULL
ORDER BY cars.brand