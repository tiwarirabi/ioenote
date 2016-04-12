<?php
/**
 * Created by PhpStorm.
 * User: rabi
 * Date: 4/12/2016
 * Time: 8:51 AM
 */

class Home extends RClass{

    function index(){
        echo "Home Page";
        $this->loadView('Home_view');
    }
}