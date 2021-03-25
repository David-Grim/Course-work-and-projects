
---------------------------------------------------------
SELECT 
	s.marketID
   ,m.numCheckStands
   ,s.checkStand
FROM 
	Markets AS m
   ,ShoppingTrips AS s
WHERE 
	s.marketID = m.marketID 
	AND m.numCheckStands < 1;
----------------------------------------------------------