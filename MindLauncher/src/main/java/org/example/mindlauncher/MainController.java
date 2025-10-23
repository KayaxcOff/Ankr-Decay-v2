package org.example.mindlauncher;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.Parent;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;

import java.io.IOException;
import java.util.Objects;

public class MainController {

    static final String GAME_PATH = "C:\\software\\Cpp\\projects\\Ankr\\cmake-build-debug-visual-studio\\Ankr.exe";

    @FXML
    private Button infoViewButton, exitButton, launcherButton;

    @FXML
    private AnchorPane main_pane;

    public void initialize() {
        launcherButton.setOnAction(e -> launchGame());
        infoViewButton.setOnAction(e -> aboutGame());
        exitButton.setOnAction(e -> quitApp());
    }

    private void launchGame() {
        try {
            ProcessBuilder processBuilder = new ProcessBuilder(GAME_PATH);
            processBuilder.start();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Could not launch the game");
            alert.setContentText("ERROR: " + e.getMessage());
            alert.setContentText("Please check the game path and try again.");
            alert.showAndWait();
            System.out.println(e.getMessage());
        }
    }

    private void aboutGame() {
        try {
            Parent view = javafx.fxml.FXMLLoader.load(Objects.requireNonNull(getClass().getResource("game-view.fxml")));
            main_pane.getChildren().setAll(view);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private void quitApp() {
        Platform.exit();
    }
}
