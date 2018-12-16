<?php session_start(); ?>

<?php if (!isset($_SESSION["swt"])) $_SESSION["swt"] = 0; ?>
<?php if (!isset($_SESSION["wdg"])) $_SESSION["wdg"] = 0; ?>

<!DOCTYPE html>

<html>
	<head>
        <title>Feux tricolores</title>        
        <meta charset="UTF-8">
        <meta http-equiv="refresh" content="2">
        
        <!-- bootstrap -->
		<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
		<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
		
		<!-- style -->
        <link rel="stylesheet" type="text/css" href="style.css">
	</head>
	
	<body>
		<?php
			$fch = "fichier.json";	// "fichier.json" | "php://input"
			if (!file_exists($fch))
			{
    			$ett = 0;
    		}
    		else
    		{
				$txtJSON = file_get_contents($fch);
				$objJSON = json_decode($txtJSON);
				if (!is_object($objJSON))
				{
					$ett = 0;
				}
				else
				{
					if ((time() - filemtime($fch)) > 40)
						$_SESSION["wdg"] = 1;
					else
						$_SESSION["wdg"] = 0;
					
					if ($_SESSION["wdg"])
					{
						$ett = 0;
					}
					else
					{
						$ett = 1;
						$feu1 = $objJSON->feu1;
						$feu2 = $objJSON->feu2;
					}
				}
			}
			
			if ($ett == 0)
			{
				if (!$_SESSION["swt"])
				{
					$feu1 = 2;
					$feu2 = 0;
				}
				else
				{
					$feu1 = 0;
					$feu2 = 2;
				}
    			$_SESSION["swt"] = 1 - $_SESSION["swt"];
			}
		?>
		<div class="container">
			<div class="row">
				<div class="col-5 decor"><img id="feu1" src=<?php if ($feu1==4) echo "vhvert.jpg"; elseif ($feu1==2) echo "vhjaune.jpg"; elseif ($feu1==1) echo "vhrouge.jpg"; else echo "vheteint.jpg";?>  height=200px></div>
				<div class="col-1" id="trait"> </div>
				<div class="col-1"> </div>
				<div class="col-5 decor"><img id="feu2" src=<?php if ($feu2==4) echo "hdvert.jpg"; elseif ($feu2==2) echo "hdjaune.jpg"; elseif ($feu2==1) echo "hdrouge.jpg"; else echo "hdeteint.jpg";?>  width=200px></div>
			</div>
			<div class="row">
				<div class="col-12 route" id="ligne"> </div>
			</div>
			<div class="row">
				<div class="col-12 route"> </div>
			</div>
			<div class="row">
				<div class="col-5 decor"><img id="feu3" src=<?php if ($feu2==4) echo "hgvert.jpg"; elseif ($feu2==2) echo "hgjaune.jpg"; elseif ($feu2==1) echo "hgrouge.jpg"; else echo "hgeteint.jpg";?>  width=200px></div>
				<div class="col-1" id="trait"> </div>
				<div class="col-1"> </div>
				<div class="col-5 decor"><img id="feu4" src=<?php if ($feu1==4) echo "vbvert.jpg"; elseif ($feu1==2) echo "vbjaune.jpg"; elseif ($feu1==1) echo "vbrouge.jpg"; else echo "vbeteint.jpg";?>  height=200px></div>
			</div>
		</div>
		<!-- bootstrap -->
		<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
		<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
		<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
	</body>
</html>

