var drawButtons = [document.getElementById("clear"), document.getElementById("interest"), document.getElementById("wall"), document.getElementById("deposit"), document.getElementById("prohibited")]
var importButton = document.getElementById("import")
var exportButton = document.getElementById("export")
var changeButton = document.getElementById("change")
var overlayButton = document.getElementById("overlay")
var divInputX = document.getElementById("xVal")
var divInputY = document.getElementById("yVal")
var inoutElement = document.getElementById("io")
var canvasElement = document.getElementById("mapper")
var canvas = canvasElement.getContext("2d")
var width = canvasElement.width
var height = canvasElement.height
var overlay = new Image

var divX = 8
var divY = 8
var lenX = 0
var lenY = 0
var map = []
var initialX = 0
var initialY = 0
var finalX = 0
var finalY = 0
var selected = 1
var time = 180
var timeSpeed = 0.75
var symbols = ["'o'", "'?'", "'#'", "'d'", "'x'"]
var dragging = false
var overlaying = false

window.onload = function () {
    var rect = canvasElement.getBoundingClientRect()
    canvasElement.addEventListener("mousedown", function (event) {
        initialX = event.clientX - rect.left + window.pageXOffset
        initialY = event.clientY - rect.top + window.pageYOffset
        dragging = true
    })
    canvasElement.addEventListener("mousemove", function(event) {
        finalX = event.clientX - rect.left + window.pageXOffset
        finalY = event.clientY - rect.top + window.pageYOffset
    })
    canvasElement.addEventListener("mouseleave", function(event) {
        dragging = false;
    })
    canvasElement.addEventListener("mouseup", function (event) {
        dragging = false
    })
    drawButtons[0].addEventListener("click", function(event) {
        selected = 0
    })
    drawButtons[1].addEventListener("click", function(event) {
        selected = 1
    })
    drawButtons[2].addEventListener("click", function(event) {
        selected = 2
    })
    drawButtons[3].addEventListener("click", function(event) {
        selected = 3
    })
    drawButtons[4].addEventListener("click", function(event) {
        selected = 4
    })
    importButton.addEventListener("click", function(event) {
        var input = inoutElement.value
        input = input.replace(/\s/g, "")
        input = input.slice(1, input.length - 2)
        var rows = input.split("},")
        divY = rows.length
        map = []
        for(var i = 0; i < rows.length; i++) {
            rows[i] = rows[i].slice(1, rows[i].length)
            var cols = rows[i].split(",")
            divX = cols.length
            map[i] = []
            for(var j = 0; j < cols.length; j++) {
                for(var k = 0; k < symbols.length; k++) {
                    if(cols[j] == symbols[k]) {
                        map[i][j] = k
                        break
                    }
                }
            }
        }
        lenX = width / divX
        lenY = height / divY
        divInputX.value = divX
        divInputY.value = divY
    })
    exportButton.addEventListener("click", function(event) {
        var output = "{"
        for(var y = 0; y < divY; y++) {
            output += "{"
            for(var x = 0; x < divX; x++) {
                output += symbols[map[y][x]]
                if(x != divX - 1) {
                    output += ","
                }
            }
            output += "}"
            if(y != divY - 1) {
                output += ","
            }
        }
        output += "}"
        inoutElement.value = output
    })
    changeButton.addEventListener("click", function(event) {
        divX = parseInt(divInputX.value)
        divY = parseInt(divInputY.value)
        /*
        if(divX > 40) {
            width = divX * 8
            canvasElement.width = divX * 8
        } else {
            width = 400
            canvasElement.width = 400
        }
        if(divY > 40) {
            height = divY * 8
            canvasElement.height = divY * 8
        } else {
            height = 400
            canvasElement.height = 400
        }
        */
        lenX = width / divX
        lenY = height / divY
        for(var y = 0; y < divY; y++) {
            map[y] = []
            for(var x = 0; x < divX; x++) {
                map[y][x] = 0
            }
        }
    })
    overlayButton.addEventListener("click", function(event) {
        overlaying = !overlaying
        if(overlaying) {
            overlayButton.textContent = "Hide overlay"
        } else {
            overlayButton.textContent = "Show overlay"
        }
    })
    loadImage.addEventListener("change", function(event) {
        if(loadImage.files.length > 0) {
            overlay.src = window.URL.createObjectURL(loadImage.files[0])
        }
    })
    for(var y = 0; y < divY; y++) {
        map[y] = []
        for(var x = 0; x < divX; x++) {
            map[y][x] = 0
        }
    }
    lenX = width / divX
    lenY = height / divY
    draw()
}

function draw() {
    canvas.fillStyle = "rgb(36, 36, 36)"
    canvas.fillRect(0, 0, width, height)
    for(var y = 0; y < divY; y++) {
        for(var x = 0; x < divX; x++) {
            if(map[y][x] == 0) {
                canvas.fillStyle = "rgb(230, 230, 230)" //clear
            } else if (map[y][x] == 1) {
                canvas.fillStyle = "hsl(" + time + ", 100%, 50%)" //interest
            } else if (map[y][x] == 2) {
                canvas.fillStyle = "rgb(127, 127, 127)" //wall
            } else if (map[y][x] == 3) {
                canvas.fillStyle = "rgb(255, 106, 0)" //orange
            } else if (map[y][x] == 4) {
                canvas.fillStyle = "rgb(255, 225, 0)" //yellow
            }
            canvas.fillRect(lenX * x, lenY * y, lenX, lenY)
            canvas.strokeStyle = "rgb(36, 36, 36)"
            canvas.strokeRect(lenX * x, lenY * y, lenX, lenY)
            canvas.lineWidth = 1
        }
    }
    time += timeSpeed
    if(time >= 280 || time <= 100) {
        timeSpeed *= -1
    }
    if(dragging) {
        var firstX = initialX
        var firstY = initialY
        var secondX = finalX
        var secondY = finalY
        if(finalX < initialX) {
            firstX = finalX
            secondX = initialX
        }
        if(finalY < initialY) {
            firstY = finalY
            secondY = initialY
        }
        firstX = Math.floor(firstX / lenX)
        firstY = Math.floor(firstY / lenY)
        secondX = Math.ceil(secondX / lenX)
        secondY = Math.ceil(secondY / lenY)
        for(var y = firstY; y < secondY; y++) {
            for(var x = firstX; x < secondX; x++) {
                map[y][x] = selected
            }
        }
    }
    if(overlaying) {
        canvas.globalAlpha = 0.4
        canvas.drawImage(overlay, 0, 0, width, height)
    }
    canvas.globalAlpha = 1
    requestAnimationFrame(draw)
}