<?php
/**
 * Created by PhpStorm.
 * User: rabi
 * Date: 4/12/2016
 * Time: 8:35 AM
 */
class Faculty extends RClass{
    function index(){
        $data['title'] = "This is the title";
        echo $this->select_query(false,array(),array('id'=>1));
        $this->loadView('Faculty_view',$data);
    }
}