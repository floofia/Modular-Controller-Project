module com.example.presentationproject {
    requires javafx.controls;
    requires javafx.fxml;


    opens presentationproject to javafx.fxml;
    exports presentationproject;
}