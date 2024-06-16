#include "handlers.h"
#include "server.h"
void stylesheet() {
  server.send(200, "text/css", R"rawliteral(button,nav p{background-color:var(--secondary)}body,button{color:var(--text)}:root{--background:#F7FAFD;--text:#000000;--primary:#dcdcdc;--secondary:#CBEBFE;--tertiary:#6F787F;--shadow:#6F787F;--border:#6F787F}@media(prefers-color-scheme:dark){:root{--background:#242424;--text:#ffffff;--primary:#242424;--secondary:#424242;--tertiary:#303030;--shadow:white;--border:#C4C4C4}}body{font-family:sans-serif;background-color:var(--background)}nav p{width:fit-content;padding:1vh 3vw;border-radius:10px}button{transition:.3s;width:20vw;height:5vh;max-height:40px;max-width:150px;border:none;border-radius:50px;font-weight:700}button[data-status=off]{border:none}button[data-status=on]{box-shadow:0 0 5px var(--shadow)}.device-child-container{transition:.3s;text-align:center;display:block;flex-grow:0;flex-shrink:1;flex-basis:auto;align-self:auto;order:0;border:solid 1px var(--border);border-radius:10px;padding:20px;width:30vw;max-height:20vh;background-color:transparent}.devices{display:flex;flex-direction:row;flex-wrap:wrap;justify-content:normal;align-items:normal;align-content:flex-start;gap:10px})rawliteral");
}

void javascript() {
  server.send(200, "text/javascript", R"rawliteral(var device_status_element=document.getElementById("device-status"),button_ids=[];function btn_flip(t){console.log("clicked");let e=document.getElementById(t.srcElement.id),n=e.getAttribute("data-pin"),i=e.getAttribute("data-status");fetch(`/flipstatus?pin=${n}`).then(t=>(t.ok||failure_handler(e,i),t.json())).then(t=>{t.error?failure_handler(e,i):"OFF"==e.textContent?(e.textContent="ON",e.setAttribute("data-status","on")):(e.textContent="OFF",e.setAttribute("data-status","off"))}).catch(t=>{console.error(t),failure_handler(e,i)})}function failure_handler(t,e){t.textContent="FAILED",setTimeout(()=>{t.textContent=e.toUpperCase()},1500)}fetch("/devices").then(t=>t.json()).then(t=>{let e=document.getElementById("device-list");t.error?device_status_element.innerHTML="backend error":(t.devices.forEach((t,n)=>{device_status_element.textContent="";let i=document.createElement("div"),o=document.createElement("h1"),d=document.createElement("button");i.classList.add("device-child-container"),o.textContent=t.name,d.textContent=t.high?"OFF":"ON",d.setAttribute("data-status",t.high?"off":"on"),d.setAttribute("data-pin",t.pin);let a=`${t.pin}-${n}`;d.setAttribute("id",a),button_ids.push(a),i.append(o),i.append(d),e.append(i)}),button_ids.forEach(t=>{console.log("adding event listener for id: "+t),document.getElementById(t).addEventListener("click",btn_flip)}))}).catch(t=>{console.error(t),device_status_element.textContent="devices fetch error"});)rawliteral");
}

void root () {
  server.send(200, "text/html", R"rawliteral(<!DOCTYPE html><html lang=en><head><meta charset=UTF-8><meta name=viewport content="width=device-width, initial-scale=1.0"><link rel=stylesheet href=style.css><title>My Home</title></head><body><nav><p>Home</p></nav><p id=device-status>Waiting...</p><div class=devices id=device-list></div><script src=script.js></script></body></html>)rawliteral");
}

void flip_pin_status() {
  if (server.hasArg("pin")) {
    int pin = server.arg("pin").toInt();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, (digitalRead(pin) == HIGH) ? LOW : HIGH);
    server.send(200, "application/json", "{ \"success\": true }");
  } else {
    server.send(500, "application/json", "{ \"error\": true }");
  }
}
