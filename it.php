<?php
if (isset($_GET["value"]))
  [$myfile = fopen("file.txt","w");
   $text = $_GET["value"];
   fwrite($myfile,$text);
   fclose($myfile);
]
?>
