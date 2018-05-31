CREATE PROCEDURE getReservedLapsPretty @dateId DATETIME
AS
SELECT reservedLaps.id, availableDates.date, cars.brand, cars.model FROM reservedLaps
LEFT JOIN availableDates ON availableDates.id = reservedLaps.dateId
LEFT JOIN cars ON cars.id = reservedLaps.carId