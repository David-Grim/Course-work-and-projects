CREATE VIEW CheapShoppingTripCost AS 
	SELECT 
		    p.shopperID
		  , p.tripTimeStamp
		  , SUM(p.quantity * p.paidPrice) AS totalCost


	FROM 
	      Purchases p,
	      ShoppingTrips s

	GROUP BY
		    p.shopperID
		  , p.tripTimeStamp
		  , p.paidPrice
		  , p.quantity
		  , p.productID
		  , s.tripTimeStamp


	HAVING
		SUM(p.paidPrice * p.quantity) < 100.00 
		AND p.quantity < 3
		AND s.tripTimeStamp = p.tripTimeStamp;




