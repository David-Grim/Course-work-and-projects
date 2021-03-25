CREATE OR REPLACE FUNCTION reduceSomePaidPricesFunction(theShopperID INTEGER, numPriceReductions INTEGER)
    RETURNS INTEGER AS $$

    DECLARE
        nextShopperID INTEGER;
        totalReductions INTEGER;
        counter INTEGER;

    DECLARE c CURSOR FOR
        SELECT 
            p.shopperID
        FROM 
            Purchases p
          , Shoppers s
          , Products pr
        WHERE 
            p.shopperID = theShopperID
            AND s.shopperID = p.shopperID
            AND s.status IS NOT NULL
            AND pr.productID = p.productID
            AND pr.regularPrice = p.paidPrice
        ORDER BY p.paidPrice DESC;

  BEGIN
    totalReductions := 0;
    counter := 0;
    OPEN c;

    WHILE totalReductions < numPriceReductions
    LOOP

        FETCH c INTO nextShopperID;
        EXIT WHEN NOT FOUND;
        totalReductions := totalReductions + 1;

        UPDATE 
            Purchases
        SET 
            paidPrice = paidPrice - 2.00
        FROM 
            Shoppers
          , Products pr
        WHERE 
            Shoppers.status = 'H'
            AND Shoppers.shopperID = Purchases.shopperID
            AND Purchases.shopperID = nextShopperID
            AND pr.productID = Purchases.productID
            AND pr.regularPrice = Purchases.paidPrice;


        UPDATE 
            Purchases
        SET 
            paidPrice = paidPrice - 1
        FROM 
            Shoppers
          , Products pr
        WHERE 
            Shoppers.status = 'M'
            AND Shoppers.shopperID = Purchases.shopperID
            AND Purchases.shopperID = nextShopperID
            AND pr.productID = Purchases.productID
            AND pr.regularPrice = Purchases.paidPrice;


        UPDATE 
            Purchases
        SET 
            paidPrice = paidPrice - .5
        FROM 
            Shoppers, Products pr
        WHERE 
            Shoppers.status = 'L'
            AND Shoppers.shopperID = Purchases.shopperID
            AND Purchases.shopperID = nextShopperID
            AND pr.productID = Purchases.productID
            AND pr.regularPrice = Purchases.paidPrice;

        counter := counter + 1;
        EXIT WHEN counter = numPriceReductions;

  END LOOP;
  CLOSE c;
  RETURN totalReductions;

END;
$$ LANGUAGE plpgsql;