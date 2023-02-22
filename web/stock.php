<?php
	$title = "Lager";
    require 'header.php';
	
    if(isset($_POST['ID']) && isset($_POST['Amount']))
	{
		$res = $db_handle->prepare('INSERT INTO products (product_id, stock) VALUES (?, ?)');
		$res->execute([$_POST['ID'], $_POST['Amount']]);
	}

    $res = $db_handle->prepare('SELECT * FROM products');
    $res->execute();
?>

	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
	
	<script>
	function ChangeStock(id, stock)
	{
		var xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function()
		{
		  if (this.readyState == 4 && this.status == 200)
		  {
			document.getElementById("txtHint").innerHTML = this.responseText;
		  }
		};
		xmlhttp.open("GET", "change_stock.php?ID=" + id + "&Amount=" + stock, true);
		xmlhttp.send();
	}
	</script>

	<ul class="menu">
		<li><a href="index.php">Hjem</a></li>
		<li><a href="#" class="active">Lager</a></li>
		<li><a href="#kontakt">Kontakt</a></li>
		<li style="float:right"><a href="#om">Om</a></li>
        <li style="float:right"><a href="product_api.php">API</a></li>
	</ul> 

	<div class="stock-list">
		<table width="50%" cellspacing="0">
			<thead>
				<th width="100">#</th>
				<th width="200">Produkt ID</th>
				<th width="100">Lager</th>
			</thead>
			<tbody>
				<?php
					while($row = $res->fetch())
					{
						echo '<tr>';
							echo '<td>' . $row['id'] . '</th>';
							echo '<td>' . $row['product_id'] . '</th>';
							echo '<td><input type="text" value="' . $row['stock'] . '" onblur="ChangeStock(' . $row['id'] . ', this.value)"></th>';
						echo '</tr>';
					}
				?>
			</tbody>
        </table>
		
		<div id="txtHint">Result: </div>

        <button onclick="location.href" id="AddProductBtn" style="margin:20px">Opret produkt</button>
	</div>
<?php
	require_once 'footer.php';
?>