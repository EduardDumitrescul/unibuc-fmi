function projectsViewMore() {
    button = document.getElementById("projects-view-more");
    button.onclick = goToProjectsPage;
}

function leaveMessage() {
    button = document.getElementById("contact-message");
    button.onclick = goToMessagePage;
}

function goToProjectsPage() {
    window.location.href = "projects.html";
}
    
function goToMessagePage() {
    window.location.href = "message.html";
}

function keyPresses() {
    document.addEventListener("keydown", (e) => {
        if (e.key === "h" || e.key == "H") {
            window.location.href = "#"
        }
        else if (e.key === "p" || e.key == "P") {
            window.location.href = "#slide-projects"
        }
        else if (e.key === "W" || e.key == "w") {
            window.location.href = "#slide-work"
        }
        else if (e.key === "e" || e.key == "E") {
            window.location.href = "#slide-education"
        }
        else if (e.key === "c" || e.key == "C") {
            window.location.href = "#slide-contact"
        } 
        else if (e.key === "a" || e.key == "A") {
            window.location.href = "#slide-awards"
        }
    });
}


keyPresses();
projectsViewMore();
leaveMessage();