<?php
if (isset($_GET["value"]))
 [
   $file = fopen("file.txt","w+");
   $text = $_GET["66"];
   fwrite($file,66);
   fclose($file);
]
