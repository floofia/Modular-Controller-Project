package presentationproject;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import presentationproject.model.ConnectedModule;
import presentationproject.view.ModuleLayout;

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    public static final int MINWIDTH = 700;
    public static final int MINHEIGHT = 350;

    public ConnectedModule[] connectedModules = {
            new ConnectedModule("x", "x", Boolean.FALSE, "x"),
            new ConnectedModule("x", "x", Boolean.FALSE, "x"),
            new ConnectedModule("x", "x", Boolean.FALSE, "x"),
            new ConnectedModule("x", "x", Boolean.FALSE, "x"),
            new ConnectedModule("x", "x", Boolean.FALSE, "x"),
            new ConnectedModule("x", "x", Boolean.FALSE, "x"),
            new ConnectedModule("x", "x", Boolean.FALSE, "x"),
            new ConnectedModule("x", "x", Boolean.FALSE, "x") };

    public void start(Stage primaryStage) {
        GridPane root = new GridPane();

        Scene scene = new Scene(root, MINWIDTH, MINHEIGHT);
        primaryStage.setMinWidth(MINWIDTH);
        primaryStage.setMinHeight(MINHEIGHT);
        primaryStage.setTitle("Modules Connected");
        primaryStage.setScene(scene);

        this.readModules();

        new ModuleLayout(root, connectedModules);

        primaryStage.show();
    }

    public void readModules() {
        ConnectedModule tempMod1 = new ConnectedModule("Address 49", "Joystick-v1", Boolean.FALSE, "joystick");
        ConnectedModule tempMod2 = new ConnectedModule("Address 51", "d-pad-v1", Boolean.FALSE, "d-pad");
        ConnectedModule tempMod3 = new ConnectedModule("Address 52", "audio-v1", Boolean.TRUE, "audio");

        connectedModules[0] = tempMod1;
        connectedModules[1] = tempMod2;
        connectedModules[2] = tempMod3;
    }
}
