<?php


class SQL_SECURITY{
	
	function strip_string($string){
        $str = mysql_escape_string($string);
        $str = htmlspecialchars($str,ENT_QUOTES,'UTF-8');
        return $str;
    }
    
    function strip_array($array){
        $new_array = array();
        foreach ($array as $key => $value) {
            $new_array[$this->strip_string($key)]=$this->strip_string($value);
        }
        return $new_array;
    }

}