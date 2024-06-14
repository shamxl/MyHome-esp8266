var device_status_element = document.getElementById("device-status")
var button_ids =  []


fetch ("/devices.json").then((response) => {
  return response.json()
}).then((data) => {
  let device_container = document.getElementById("device-list")
  if (data.error) {
    device_status_element.innerHTML = "backend error"
  } else {
    data.devices.forEach((device, index) => {
      device_status_element.textContent = ""
      let device_children_container = document.createElement("div")
      let device_children_name = document.createElement("h1")
      let device_children_button = document.createElement("button")

      device_children_container.classList.add("device-child-container")

      device_children_name.textContent = device.name
      device_children_button.textContent = device.high ? "ON" : "OFF"
      device_children_button.setAttribute("data-status", device.high ? "on" : "off")
      device_children_button.setAttribute("data-pin", device.pin)
      let id = `${device.pin}-${index}`
      device_children_button.setAttribute("id", id)
      button_ids.push(id)
      device_children_container.append(device_children_name)
      device_children_container.append(device_children_button)
      device_container.append(device_children_container)
    })

    button_ids.forEach(id => {
      console.log("adding event listener for id: "+id)
      document.getElementById(id).addEventListener("click", btn_flip)
    })

  }
}).catch((err) => {
  console.error(err)
  device_status_element.textContent = "devices fetch error"
})




function btn_flip (element) {
  console.log("clicked")
  let doc = document.getElementById(element.srcElement.id)
  let pin = doc.getAttribute("data-pin")
  let pin_status = doc.getAttribute("data-status")

  if (doc.textContent == "WAITING") {

    return false
  }

  doc.textContent = "WAITING"

  fetch(`/flipstatus?pin=${pin}`).then(response => {
    if (!response.ok) {
      failure_handler(doc, pin_status)

    }

    return json.response()
  }).then(data => {
    if (data.error) {
      failure_handler(doc, pin_status)
    } else {
      if (doc.textContent == "OFF") {
        doc.textContent = "ON"
        doc.setAttribute("data-status", "on")
      } else {
        doc.textContent = "OFF"
        doc.setAttribute("data-status", "off")
      }
    }

  }).catch((err) => {
    console.error(err)
    failure_handler(doc, pin_status)
  })



}

function failure_handler (doc, pin_status) {
  doc.textContent = "FAILED"
  setTimeout(() => {
    doc.textContent = pin_status.toUpperCase()
  }, 1500)

}


// im sorry :3
