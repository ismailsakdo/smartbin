function doGet() {
  return HtmlService.createHtmlOutputFromFile("index");
}

function recordData(name, email, phone, date, option) {
  var sheet = SpreadsheetApp.openById("your_google_sheet_id").getActiveSheet();
  var rowData = [name, email, phone, date, option];
  sheet.appendRow(rowData);

  updateThingSpeak(); // Update ThingSpeak regardless of the option

  // Set a delay to reset ThingSpeak status after 30 seconds (30000 milliseconds)
  Utilities.sleep(15000); // Wait for 30 seconds
  resetThingSpeak();
}

function updateThingSpeak() {
  var url = "https://api.thingspeak.com/update.json";
  var apiKey = "your_thingspeak_write_api";
  var fieldNumber = 1;

  var data = {
    api_key: apiKey,
    field1: "1" // Set the field value to "1" to trigger the action
  };

  var options = {
    method: "post",
    contentType: "application/json",
    payload: JSON.stringify(data)
  };

  UrlFetchApp.fetch(url, options);
}

function resetThingSpeak() {
  var url = "https://api.thingspeak.com/update.json";
  var apiKey = "your_thingspeak_write_api";
  var fieldNumber = 1;

  var data = {
    api_key: apiKey,
    field1: "0" // Set the field value back to "0"
  };

  var options = {
    method: "post",
    contentType: "application/json",
    payload: JSON.stringify(data)
  };

  UrlFetchApp.fetch(url, options);
}
