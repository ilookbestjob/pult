$(function () {
  buildButtons(".pult__buttons");

  checkchanges();

  ///////////////////////действия
  $("#log").click(function () {
    displayLogs();
  });

  $("#setup").click(function () {
    displaySetup();
  });

  $(".savebutton").click(function () {
    saveSetup();
  });

  $(".cancelbutton").click(function () {
    $(".buttondialog").fadeOut();
  });
});

const prepareButtons = (count = 16) => {
  let buttons = [];
  let names = [
    "Возврат",
    "10 метров",
    "15 метров",
    "20 метров",
    "25 метров",
    "30 метров",
    "40 метров",
    "50 метров",
    "60 метров",
    "70 метров",
    "80 метров",
    "90 метров",
    "100 метров",
    "110 метров",
    "Назад",
    "Вперед",
  ];
  for (let t = 1; t <= count; t++) {
    buttons.push({ name: names[t - 1] });
  }
  return buttons;
};

const buildButtons = (
  target,
  buttons = prepareButtons(),
  demensions = { width: 4, height: 4 }
) => {
  $(target).html();
  $(target).css({
    "grid-template-columns": "repeat(" + demensions.width + ", 1fr)",
  });
  $(target).css({
    "grid-template-rows": "repeat(" + demensions.height + ", 1fr)",
  });
  buttons.forEach((button, index) => {
    $(target).append(
      '<div class="button" ><div class="button__status ' +
        ["pushed", "blured", "notpushed"][Math.floor(Math.random() * 2)] +
        '">&nbsp;</div><div class="button__name">' +
        button.name +
        '</div><div class="button__setup"><img class="setupimage" number="' +
        (index + 1) +
        '" src="setup.png"/></div></div>'
    );
  });
  $(".setupimage").click(function () {displayButtonSetup($(this).attr("number"))});

};

const displayLogs = () => {
  $("#log").addClass("active");
  $("#setup").removeClass("active");
  $(".logcontainer").fadeIn();
  $(".setupcontainer").hide();
};
const displaySetup = () => {
  $("#setup").addClass("active");
  $("#log").removeClass("active");
  $(".setupcontainer").fadeIn();
  $(".logcontainer").hide();
};

const checkchanges = () => {
  $(".group")
    .find("input")
    .keypress(function () {
      $(".savebutton").fadeIn(100);
    });
};

const saveSetup = () => {
  $(".savebutton").fadeOut(100);
};

const displayButtonSetup = (number) => {
 $(".buttondialog").fadeIn();
  $(".buttondialog")
    .find(".buttondialog__header")
    .html("Настройка кнопки #" + number);
};
