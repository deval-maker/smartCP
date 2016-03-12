<?php 

	// This file makes a connection with mysql database. 
	require_once("pass.php");

	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	if ($conn->connect_error) {
	    die("Connection failed: " . $conn->connect_error);
	} 

	if(isset($_GET['q'])){

	    $q = htmlspecialchars($_GET["q"]);

	    $sql = "SELECT * FROM `OfficialTimings` WHERE `shopName`=". "\"" . $q. "\"";
		$res = $conn->query($sql);
		$result = mysqli_fetch_array($res); 
		$str="";
		if ($result["currStatus"] == 1 )
			$shopStatus="Open";
		else 
			$shopStatus="Closed";

		if ($res->num_rows > 0) {

	    	$str.= "<h2 > " . $result["shopName"] . "</h2>
					<ul>
					<li></li>
					<li >Current Status: " .$shopStatus."</li>
					<li>Opening Time :" . $result["open"] . " Hrs <br> <br> Closing Time :". $result["close"] . "Hrs </li>
					</ul> ";

			echo $str;
		    
		} else {
		    echo "No results";
		}

	}else{
	    echo "GET variable q is not set.";
	}

	$conn->close();
?>