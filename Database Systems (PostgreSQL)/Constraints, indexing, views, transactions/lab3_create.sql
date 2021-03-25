-- Lab3 create.sql

DROP SCHEMA Lab3 CASCADE;
CREATE SCHEMA Lab3;

-- Create tables

-- Shoppers(shopperID, shopperName, address, joinDate, status)
CREATE TABLE Shoppers (
	shopperID INTEGER, 
	shopperName VARCHAR(40), 
	address VARCHAR(60), 
	joinDate DATE,
    status CHAR(1),
	PRIMARY KEY (shopperID)
);

-- Products(productID, productName, manufacturer, regularPrice)
CREATE TABLE Products (
	productID INTEGER, 
	productName VARCHAR(40), 
	manufacturer VARCHAR(40),
    regularPrice NUMERIC(5,2),
	PRIMARY KEY (productID)
);
 
-- Markets(marketID, address, managerID, numCheckStands)
CREATE TABLE Markets (
	marketID INTEGER,
	address VARCHAR(60),
    managerID INTEGER,
	numCheckStands INTEGER,
	PRIMARY KEY (marketID)
);

-- Employees(empID, empName, marketID, hireDate, level, stillEmployed)
CREATE TABLE Employees (
	empID INTEGER,
    empName VARCHAR(40),
    marketID INTEGER,
	hireDate DATE,
	level CHAR(1),
	stillEmployed BOOLEAN,
	PRIMARY KEY (empID)
);

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
    FOREIGN KEY (checkerID) REFERENCES Employees(empID)       
); 

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


-- PurchaseChanges(shopperID,  tripTimeStamp, productID, paidPrice)
CREATE TABLE PurchaseChanges (
	shopperID INTEGER,
	tripTimestamp TIMESTAMP,
	productID INTEGER,
	paidPrice NUMERIC(5,2),
    PRIMARY KEY (shopperID, tripTimeStamp, productID),
    FOREIGN KEY (shopperID, tripTimestamp) REFERENCES ShoppingTrips,
	FOREIGN KEY (productID) REFERENCES Products
);

