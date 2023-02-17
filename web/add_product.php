<?php
	$title = "Opret produkt";
    require 'header.php';
	
	if(isset($_POST['ID']) && isset($_POST['Amount']))
	{
		$res = $db_handle->prepare('INSERT INTO products (product_id, stock) VALUES (?, ?)');
		$res->execute([$_POST['ID'], $_POST['Amount']]);
	}
?>

	<ul class="menu">
		<li><a href="#" class="active">Hjem</a></li>
		<li><a href="stock.php">Lager</a></li>
		<li><a href="#kontakt">Kontakt</a></li>
		<li style="float:right"><a href="#om">Om</a></li>
        <li style="float:right"><a href="product_api.php">API</a></li>
	</ul> 

	<div>
		<form action="/stock.php" method="POST">
			<label for="ProduktId">Produkt ID:</label>
			<input type="text" id="ID" name="ID"><br />

			<label for="Stock">Antal:</label>
			<input type="text" id="Amount" name="Amount"><br />

			<input type="submit" value="Opret">
		</form>
	</div>

<?php
	require_once 'footer.php';
?>