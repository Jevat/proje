<?php
//if (isset($_GET["value"]))
 // [
   $myfile = fopen("file.txt","w");
   $text = $_GET["66"];
   fwrite($myfile,$text);
   fclose($myfile);
//]
?>
