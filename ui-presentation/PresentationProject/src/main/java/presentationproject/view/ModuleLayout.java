package presentationproject.view;

import javafx.geometry.HPos;
import javafx.geometry.Pos;
import javafx.geometry.VPos;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import presentationproject.model.ConnectedModule;

public class ModuleLayout {
    public ModuleLayout(GridPane root, ConnectedModule[] connectedModules) {
        for( int i = 0; i < 8; i ++ ) {
            Text label = new Text();
            ImageView moduleImg;
            ConnectedModule temp = connectedModules[i];

            if (!temp.getAddress().equals("x")) {
                String text = temp.getAddress() + ": " + temp.getName();
                label.setText(text);

                if(temp.getModType().equals("audio")) {
                    moduleImg = new ImageView(new Image("C:\\Users\\7182094\\IdeaProjects\\PresentationProject\\src\\main\\resources\\audio.png"));
                } else if(temp.getModType().equals("d-pad")) {
                    moduleImg = new ImageView(new Image("C:\\Users\\7182094\\IdeaProjects\\PresentationProject\\src\\main\\resources\\dpad.png"));
                } else if(temp.getModType().equals("joystick")) {
                    moduleImg = new ImageView(new Image("C:\\Users\\7182094\\IdeaProjects\\PresentationProject\\src\\main\\resources\\joystick.png"));
                } else {
                    moduleImg = new ImageView(new Image("C:\\Users\\7182094\\IdeaProjects\\PresentationProject\\src\\main\\resources\\unknown.png"));
                }
            } else {
                label.setText("Disconnected");
                moduleImg = new ImageView(new Image("C:\\Users\\7182094\\IdeaProjects\\PresentationProject\\src\\main\\resources\\disconnected.png"));
            }

            int col = i % 4;
            int row = i / 4;
            VBox box = new VBox(5);
            box.setAlignment(Pos.CENTER);
            box.getChildren().addAll(moduleImg, label);
            root.add(box, col, row);
        }

        root.setHgap(5);
        root.setVgap(5);
        ColumnConstraints col = new ColumnConstraints();
        col.setHalignment(HPos.CENTER);
        col.setPercentWidth(25);
        root.getColumnConstraints().add(col);

        RowConstraints row = new RowConstraints();
        row.setValignment(VPos.CENTER);
        row.setPercentHeight(50);
        root.getRowConstraints().add(row);
    }
}
