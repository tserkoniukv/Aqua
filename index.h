const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=0.8" charset="UTF-8">
<style>
* {box-sizing: border-box}

/* Set height of body and the document to 100% */
body, html {
  height: 100%;
  margin: 0;
  font-family: Arial;
}

/* Style tab links */
.tablink {
  background-color: #555;
  color: white;
  float: left;
  border: none;
  outline: none;
  cursor: pointer;
  padding: 14px 16px;
  font-size: 17px;
  width: 33.33%;
}

.tablink:hover {
  background-color: #777;
}

/* Style the tab content (and add height:100% for full page content) */
.tabcontent {
  color: white;
  display: none;
  padding: 10px 10px;
  height: 100%;
}

#Control {background-color: orange;}
#Params {background-color: olive;}
#About {background-color: green;}

#rectangle {
    width: 25px;
    height: 25px;
    background: #4da1f7;
    display: inline-block;
}

.slidecontainer {
  width: 100%;
}

.slider {
  -webkit-appearance: none;
  width: 80%;
  height: 25px;
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
}

.slider:hover {
  opacity: 1;
}

.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 25px;
  height: 25px;
  background: #4CAF50;
  cursor: pointer;
}

.slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  background: #4CAF50;
  cursor: pointer;
}
</style>
</head>
<body>

<button class="tablink" onclick="openPage('Control', this, 'red')" id="defaultOpen">Управление</button>
<button class="tablink" onclick="openPage('Params', this, 'red')" >Параметры</button>
<button class="tablink" onclick="openPage('About', this, 'green')">О программе</button>

<div id="Control" class="tabcontent">
  <h3>Управление</h3>
  <p>Светодиодные лампы:</p>
  <div class="slidecontainer">
  <p><div id="rectangle" style="background: #FFFFFF"></div>
  <input type="range" name="WCValue" min="1" max="100" class="slider" id="WCRange">
  <span id="WCV" style="color:black; font-size:150%; vertical-align: top;"></span></p>
  <p><div id="rectangle" style="background: #FFFF99"></div>
  <input type="range"  name="WWValue" min="1" max="100" class="slider" id="WWRange">
  <span id="WWV" style="color:black; font-size:150%; vertical-align: top;"></span></p>
  <p><div id="rectangle" style="background: #FF0000"></div>
  <input type="range"  name="RedValue" min="1" max="100" class="slider" id="RedRange">
  <span id="RedV" style="color:black; font-size:150%; vertical-align: top;"></span></p>
  <p><div id="rectangle" style="background: #00FF00"></div>
  <input type="range"  name="GreenValue" min="1" max="100" class="slider" id="GreenRange">
  <span id="GreenV" style="color:black; font-size:150%; vertical-align: top;"></span></p>
  <p><div id="rectangle" style="background: #0000FF"></div>
  <input type="range"  name="BlueValue" min="1" max="100" class="slider" id="BlueRange">
  <span id="BlueV" style="color:black; font-size:150%; vertical-align: top;"></span></p>
  <p><div id="rectangle" style="background: #9900FF"></div>
  <input type="range"  name="UVValue" min="1" max="100" class="slider" id="UVRange">
  <span id="UVV" style="color:black; font-size:150%; vertical-align: top;"></span></p>
  <br>
  <button type="button" onclick="sendLampsData()">Применить</button>
  <br>
  Return from server : <span id="ServerText">NA</span><br>
  </form>
</div>
</div>

<div id="Params" class="tabcontent">
  <h3>Параметры</h3>
  <p>Здесь будут параметры аквариума</p> 
</div>

<div id="About" class="tabcontent">
  <h3>About</h3>
  <p>Who we are and what we do.</p>
</div>

<script>
function openPage(pageName,elmnt,color) {
  var i, tabcontent, tablinks;
  tabcontent = document.getElementsByClassName("tabcontent");
  for (i = 0; i < tabcontent.length; i++) {
    tabcontent[i].style.display = "none";
  }
  tablinks = document.getElementsByClassName("tablink");
  for (i = 0; i < tablinks.length; i++) {
    tablinks[i].style.backgroundColor = "";
  }
  document.getElementById(pageName).style.display = "block";
  elmnt.style.backgroundColor = color;
}

// Get the element with id="defaultOpen" and click on it
document.getElementById("defaultOpen").click();

var WCslider = document.getElementById("WCRange");
var WWslider = document.getElementById("WWRange");
var Redslider = document.getElementById("RedRange");
var Greenslider = document.getElementById("GreenRange");
var Blueslider = document.getElementById("BlueRange");
var UVslider = document.getElementById("UVRange");
var output1 = document.getElementById("WCV");
var output2 = document.getElementById("WWV");
var output3 = document.getElementById("RedV");
var output4 = document.getElementById("GreenV");
var output5 = document.getElementById("BlueV");
var output6 = document.getElementById("UVV");

GetVFunction();

WCslider.oninput = function() {
  output1.innerHTML = this.value;
}
WWslider.oninput = function() {
  output2.innerHTML = this.value;
}
Redslider.oninput = function() {
  output3.innerHTML = this.value;
}
Greenslider.oninput = function() {
  output4.innerHTML = this.value;
}
Blueslider.oninput = function() {
  output5.innerHTML = this.value;
}
UVslider.oninput = function() {
  output6.innerHTML = this.value;
}

function sendLampsData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ServerText").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "setLamps?wc="+WCslider.value+"&ww="+WWslider.value+"&r="+Redslider.value+"&g="+Greenslider.value+"&b="+Blueslider.value+"&uv="+UVslider.value, true);
  xhttp.send();
}

function GetVFunction() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var s = this.responseText;
      document.getElementById("ServerText").innerHTML = s;
      var arr = s.split(" ");
      WCslider.value = arr[0];
      WWslider.value = arr[1];
      Redslider.value = arr[2]; 
      Greenslider.value = arr[3]; 
      Blueslider.value = arr[4]; 
      UVslider.value = arr[5];
      output1.innerHTML = arr[0];
      output2.innerHTML = arr[1];
      output3.innerHTML = arr[2];
      output4.innerHTML = arr[3];
      output5.innerHTML = arr[4];
      output6.innerHTML = arr[5];
    }
  };
  xhttp.open("GET", "getParams", true);
  xhttp.send();
}

</script>
   
</body>
</html> 
)=====";
