


var submitButton = document.getElementById("submit-button");
var nameInput = document.getElementById("input-name");
var emailInput = document.getElementById("input-email");
var messageInput = document.getElementById("input-message");



function submitButtonClick() {
    submitButton.addEventListener("click", disable);
    submitButton.onclick = function() {
        setTimeout(alertSend, 1000);

        localStorage.setItem("name", nameInput.value);
        localStorage.setItem("email", emailInput.value);
        localStorage.setItem("msg", messageInput.value);
    }
}
function disable(ev) {
     ev.target.style.display = "none";
}

function alertSend() { 
    if(validateEmail(localStorage.getItem("email")))
        alert("You message has been sent!" + "\n" + "Name: " + localStorage.getItem("name") + "\n" + "Email: " + localStorage.getItem("email") + "\n" + "Message: " + localStorage.getItem("msg"));
    else
        alert("Invalid Email");
}

const validateEmail = (email) => {
    return String(email)
      .toLowerCase()
      .match(
        /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|.(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/
      );
  };

submitButtonClick();