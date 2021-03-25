-----------------------------------------------------------
SELECT
  s.shopperID AS sid 
 ,s.shopperName AS sname 
 ,s.address AS saddress
FROM
  Shoppers s,
  ShoppingTrips t,
  Employees e
WHERE 
  t.checkerID = e.empID 
  AND s.shopperID = t.shopperID 
  AND t.tripTimestamp > '2019-10-28 15:00:00' 
  AND e.empName = 'Emma Wang'
GROUP BY 
  s.shopperID
 ,s.shopperName
 ,s.address
HAVING COUNT(t.marketID) > 1;
----------------------------------------------------------