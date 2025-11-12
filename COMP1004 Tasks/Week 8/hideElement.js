//console.log("Linked")


function hide_element()
{
    var x = document.getElementById("cheese_burger");
    //console.log("clicked");
    if (x.style.display === "none")
    {
        x.style.display = "block";
    }
    else
    {
        x.style.display="none";
    }
}

function change_theme()
{
    //console.log("Theme change button pressed");
    var x = document.getElementById("page_theme");
    //console.log(x.getAttribute("href"));
    if (x.getAttribute("href")=="light theme.css")
    {
        x.href="dark theme.css";    
    }
    else
    {
        x.href="light theme.css";
    }
    store_theme();
}

function revert()
{
    var x = document.getElementById("cheese_burger");
    x.src="download.png"
}

function change_image()
{
    //console.log("Image change button pressed");
    var x = document.getElementById("cheese_burger");
    //x.setAttribute("src", "the goat.png")
    x.setAttribute("src", "idk.gif");
    const timeout = setTimeout(revert,1000);
}

function store_theme()
{
    localStorage.setItem("token", document.getElementById("page_theme").getAttribute("href"))
}

function set_theme()
{
    var bg = localStorage.getItem("token");
    console.log(bg);
    document.getElementById("page_theme").href=bg;
}