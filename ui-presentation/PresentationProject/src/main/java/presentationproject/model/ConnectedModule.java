package presentationproject.model;

public class ConnectedModule {
    // each named after input name from Controller Settings GUI Communication Example document
    protected String address;
    protected String name;
    protected Boolean feedbackDeviceStatus;
    protected String modType;

    public ConnectedModule(String address, String name, Boolean feedbackDeviceStatus, String modType) {
        this.address = address;
        this.name = name;
        this.feedbackDeviceStatus = feedbackDeviceStatus;
        this.modType = modType;
    }

    public String getAddress() {
        return this.address;
    }

    public String getName() {
        return this.name;
    }

    public Boolean isFeedbackDevice() {
        return this.feedbackDeviceStatus;
    }

    public String getModType() {
        return this.modType;
    }
}
