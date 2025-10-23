package org.example.mindlauncher;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.Parent;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;

import java.util.Objects;

public class GameController {

    @FXML
    private Button launchButton, exitButton;

    @FXML
    private AnchorPane main_pane;

    public void initialize() {
        launchButton.setOnAction(e -> launchGame());
        exitButton.setOnAction(e -> quitApp());
    }

    private void launchGame() {
        try {
            Parent view = javafx.fxml.FXMLLoader.load(Objects.requireNonNull(getClass().getResource("launcher-view.fxml")));
            main_pane.getChildren().setAll(view);
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Could not load the game view");
            alert.setContentText("ERROR: " + e.getMessage());
            alert.showAndWait();
            System.out.println(e.getMessage());
        }
    }

    private void quitApp() {
        Platform.exit();
    }
}
