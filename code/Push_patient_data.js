function doGet(e){
  
  var row = 0;
  var check = false; 

  var ss = SpreadsheetApp.getActive();

  var sheet = ss.getSheetByName(e.parameter["id"]);

  var values = sheet.getDataRange().getValues()

  var headers = sheet.getRange(1, 1, 1, sheet.getLastColumn()).getValues()[0];

  for(n=0;n<values.length;n++)
  {
    var cell = values[n][2];

    if(cell == e.parameter[headers[2]])
       {
         check = true;
         row = n;
         break;
       }
  }
  
  var lastRow = sheet.getLastRow();

  var cell = sheet.getRange('a1');
  var col = 0;
  var d = new Date();

  for (i in headers){

    // loop through the headers and if a parameter name matches the header name insert the value

    if (headers[i] == "Time")
    {
      val = d.toDateString() + ", " + d.toLocaleTimeString();
    }

    else
    {
      val = e.parameter[headers[i]]; 
    }

    // append data to the last row
    if(check == true)
    {
      cell.offset(row,col).setValue(val)
    }
    else
    {
       cell.offset(lastRow, col).setValue(val);
    }

    col++;
  }

  return ContentService.createTextOutput('success');
}