<?php
	$title = "Forside";
    require 'header.php';
	
	if(isset($_GET['ID']))
	{
		$res = $db_handle->prepare('SELECT * FROM products WHERE id = ?');
		$res->execute([$_GET['ID']]);
		echo '<table>';
		echo '<tr>';
		echo '<th>ID</th>';
		echo '<th>ProductId</th>';
		echo '<th>Stock</th>';
		echo '</tr>';
		echo '<tr>';
		while($row = $res->fetch())
		{
			echo '<th>' . $row['id'] . '</th>';
			echo '<th>' . $row['product_id']. '</th>';
			echo '<th>' . $row['stock'] . '</th>';
		}
		echo '</tr>';
		echo '</table>';
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
		<form action="/index.php" method="POST">
			<label for="ProduktId">Produkt ID:</label>
			<input type="text" id="ProduktId" name="ProduktId"><br />

			<label for="Stock">Lager:</label>
			<input type="text" id="Stock" name="Stock"><br />

			<input type="submit" value="Opret">
		</form>
	</div>

<?php
	require_once 'footer.php';
?>