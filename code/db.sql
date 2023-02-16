CREATE TABLE IF NOT EXISTS `products`
(
	`id`			INT,
	`product_id`	VARCHAR(64) NOT NULL,
	`stock`			INT			NOT NULL,
	
	PRIMARY KEY (`id`)
);

INSERT INTO products(id, product_id, stock) VALUES (1, 'TX-302587', 231);
INSERT INTO products(id, product_id, stock) VALUES (2, 'NETGEAR-CM1000', 57);
INSERT INTO products(id, product_id, stock) VALUES (3, 'COAX_CABEL_20M', 999);
INSERT INTO products(id, product_id, stock) VALUES (4, 'F-CONNECT', 178);
INSERT INTO products(id, product_id, stock) VALUES (5, '#8300129182', 18);
INSERT INTO products(id, product_id, stock) VALUES (6, '#LABEL-RETUR', 12);