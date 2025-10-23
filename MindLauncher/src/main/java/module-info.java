module org.example.mindlauncher {
    requires javafx.controls;
    requires javafx.fxml;


    opens org.example.mindlauncher to javafx.fxml;
    exports org.example.mindlauncher;
}