function seeProjectList() {
    titles = ["Focus", "NBA-simulator", "Darwin-Sim", "Hexagon Dijkstra", "Sorter"];
    descpriptions = [
    "Welcome to Focus – a minimalistic productivity app for Android users! This app is designed to help you stay on task and increase your productivity by measuring the amount of time you spend focused on your work. Then, we convert this time into points, which can be used to upgrade your stats and improve your ability to focus for longer periods of time.",
    "An Object Oriented Programming project which tries to model a Basketball League and allows the user to add his personalized players, teams and simulate games and seasons.",
    "This project tries to replicate natural selection using entities that are born with a set of attributes which determine their ability to survive and replicate. Every new generation, there is a chance that mutations appear, so the stronger individuals have increased chance to live linger and transmit their genes.",
    "A visualizer for the Dijkstra's Algorithm for path finding, but running on a grid of hexagons.",
    "This projects focuses on comparing various sorting algorithms  (such as Count Sort, Merge Sort, Heap Sort, Radix Sort, Shell Sort and the C++ standard sort) on different data sets). <br>  All the results have been plotted using Python's Matplotlib."
    ];
    imgSrc = ["res/images/focus.png", "res/images/nba-sim.png", "res/images/darwin-sim.png", "res/images/hex-small.png", "res/images/sorting.png"];

    links = [
        "https://github.com/EduardDumitrescul/Focus",
        "https://github.com/EduardDumitrescul/nba_poo",
        "https://github.com/EduardDumitrescul/darwin-sim",
        "https://github.com/EduardDumitrescul/java-projects/tree/main/hexagon-dijkstra",
        "https://github.com/EduardDumitrescul/lfa_finite_auto"
    ]


    for(let i = 0; i <titles.length; i ++) {
        container = document.createElement("div");
        container.style.display = "flex";
        container.style.margin = "4em";

        img = document.createElement("img");
        img.src = imgSrc[i];
        size = Math.random() * 5 + 15;
        img.style.height = size + "vh";
        img.style.aspectRatio = "1/1";
        img.style.marginRight = "2em";
        img.className += "img-squircle";
        container.appendChild(img);

        column = document.createElement("div");
        title = document.createElement("h1");
        title.innerHTML =  titles[i];
        column.appendChild(title);
        desc = document.createElement("h3");
        desc.innerHTML = descpriptions[i];
        column.appendChild(desc);


        var checkboxDiv = document.createElement("div");

        var checkbox = document.createElement("input");
        checkbox.type = "checkbox";
        checkbox.name = "links";

        checkboxDiv.appendChild(checkbox);



        label = document.createElement("label");
        label.for  = "links";
        label.innerHTML = "view links";
        checkboxDiv.appendChild(label);

        column.appendChild(checkboxDiv);

        link = document.createElement("a");
        link.href = links[i];
        link.target = "blank";
        link.id = "github-link" + i;
        link.innerHTML = "Go to Github repository";
        link.style.visibility = "hidden";
        column.appendChild(link);


        container.appendChild(column);
        document.body.appendChild(container);


        checkbox.onclick = function(){
            linkk = document.getElementById("github-link"+i);
            if(linkk.style.visibility === "hidden") {
                linkk.style.visibility = "visible";
            }
            else {
                linkk.style.visibility = "hidden";
            }
        }
    }

}

function setImgSquircle() {
    elements = document.getElementsByClassName("img-squircle");
    for(let el of elements) {
        console.log(el);
        el.style.borderRadius = "5%";
    }
}


seeProjectList();

setImgSquircle();