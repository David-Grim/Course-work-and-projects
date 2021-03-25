BEGIN TRANSACTION ISOLATION LEVEL SERIALIZABLE;

/*	If there already is a tuple in the Purchases table which has that shopperID, tripTimestamp and productID,
	then update the tuple in Purchases that has that shopperID, tripTimestamp and productID. Update
	paidPrice for that existing Purchases tuple based on the value of paidPrice in the PurchaseChanges tuple,
	and increase quantity by 2.*/
	
UPDATE Purchases
	SET 
		paidPrice = p.paidPrice
	  , quantity = quantity + 2

	FROM 
		PurchaseChanges  AS p
	WHERE 
		Purchases.shopperID = p.shopperID 
		AND Purchases.tripTimeStamp = p.tripTimeStamp
		AND Purchases.productID = p.productID;

/*-- If there isn’t already a tuple in the Purchases table which has that shopperID, tripTimestamp and
  -- productID, then insert a tuple into the Purchases table corresponding to that PurchaseChanges tuple. Use
  -- paidPrice as provided in the PurchaseChanges tuple, and set quantity to 1*/

INSERT INTO Purchases(shopperID,  tripTimeStamp, productID, quantity, paidPrice)
	SELECT 
		p.shopperID
	  , p.tripTimeStamp
	  , p.productID
	  , 1
	  , p.paidPrice
	FROM 
		PurchaseChanges AS p
	WHERE NOT EXISTS (SELECT * 
					  FROM 
					  	 Purchases AS p2
					  WHERE 
					  	  p2.shopperID = p.shopperID 
						  AND p2.tripTimeStamp = p.tripTimeStamp
						  AND p2.productID = p.productID);


COMMIT;