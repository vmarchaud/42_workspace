<?PHP
    session_start();
    
    if ($_GET['login'] && $_GET['passwd']) {
        $_SESSION['login'] = $_GET['login'];
        $_SESSION['passwd'] = $_GET['passwd'];
    }
    
    echo "<html><body>\n";
    echo '<form action="index.php" method="get">';
    echo 'Identifiant: <input type="text" name="login" value="' . $_SESSION['login'] . '" />';
    echo "<br />\n";
    echo 'Mot de passe: <input type="password" name="passwd" value="' . $_SESSION['passwd'] .'" />';
    echo '<input type="submit" type="button" name="submit" value="OK"/>';
    echo "</form>\n";
    echo "</html></body>\n";
?>