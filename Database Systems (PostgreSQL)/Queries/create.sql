-- For Lab2, our Solution for Lab1 is the base file that you'll have to modify

--DROP SCHEMA CASCADE and CREATE SCHEMA statements can appear, but aren't required

DROP SCHEMA Lab2 CASCADE;
CREATE SCHEMA Lab2;


-- Create tables

-- Shoppers(shopperID, shopperName, address, joinDate, status)
CREATE TABLE Shoppers (
	shopperID INTEGER, 
	shopperName VARCHAR(40), 
	address VARCHAR(60), 
	joinDate DATE,
    status CHAR(1),
    UNIQUE(shopperName,address),
	PRIMARY KEY (shopperID)
);
-- shopperID INTEGER PRIMARY KEY is also correct

-- Products(productID, productName, manufacturer, regularPrice)
CREATE TABLE Products (
	productID INTEGER, 
	productName VARCHAR(40), 
	manufacturer VARCHAR(40),
    regularPrice NUMERIC(5,2) NOT NULL,
    UNIQUE(productName, manufacturer),
	PRIMARY KEY (productID)
);
--productID INTEGER PRIMARY KEY is also correct 
-- regularPrice DECIMAL(5,2) is also correct
 
-- Markets(marketID, address, managerID, numCheckStands)
CREATE TABLE Markets (
	marketID INTEGER,
	address VARCHAR(60),
    managerID INTEGER,
	numCheckStands INTEGER NOT NULL,
	UNIQUE(address),
	PRIMARY KEY (marketID)
);
-- marketID INTEGER PRIMARY KEY is also correct

-- Employees(empID, empName, marketID, hireDate, level, stillEmployed)
CREATE TABLE Employees (
	empID INTEGER,
    empName VARCHAR(40),
    marketID INTEGER,
	hireDate DATE,
	level CHAR(1),
	stillEmployed BOOLEAN NOT NULL,
	PRIMARY KEY (empID),
	FOREIGN KEY (marketID) REFERENCES Markets
);
-- empID INTEGER PRIMARY KEY is also correct
-- FOREIGN KEY (marketID) REFERENCES Markets (marketID) is also correct

-- ShoppingTrips(shopperID, tripTimestamp, marketID, empID, payType, paymentValid)
CREATE TABLE ShoppingTrips (
	shopperID INTEGER,
	tripTimestamp TIMESTAMP,
	marketID INTEGER,
    checkStand INTEGER,
    checkerID INTEGER,
	payType CHAR(1),
	paymentValid BOOLEAN,
    PRIMARY KEY (shopperID, tripTimeStamp),
	FOREIGN KEY (shopperID) REFERENCES Shoppers,
	FOREIGN KEY (marketID) REFERENCES Markets,
    FOREIGN KEY (checkerID) REFERENCES Employees(empID)       
); 
-- FOREIGN KEY (shopperID) REFERENCES Shoppers(shopperID) is also correct
-- FOREIGN KEY (marketID) REFERENCES Markets (marketID) is also correct   

-- Purchases(shopperID,  tripTimeStamp, productID, quantity, paidPrice)
CREATE TABLE Purchases (
	shopperID INTEGER,
	tripTimestamp TIMESTAMP,
	productID INTEGER,
	quantity INTEGER,
	paidPrice NUMERIC(5,2),
    PRIMARY KEY (shopperID, tripTimeStamp, productID),
    FOREIGN KEY (shopperID, tripTimestamp) REFERENCES ShoppingTrips,
	FOREIGN KEY (productID) REFERENCES Products
);
-- paidPrice DECIMAL (5,2) is also correct
-- FOREIGN KEY (shopperID, tripTimestamp) REFERENCES ShoppingTrips(shopperID, tripTimestamp) is also correct
-- FOREIGN KEY (productID) REFERENCES Products (productID) is also correct
