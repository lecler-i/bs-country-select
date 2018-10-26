open Css;

let searchIconUrl = [%bs.raw {|require('../../../assets/search-icon.svg')|}];
let dropdownArrowUrl = [%bs.raw
  {|require('../../../assets/dropdown-arrow.svg')|}
];

let inputSearchIconSize = 20;

global(
  ".Select-control",
  [
    important(backgroundImage(url(searchIconUrl))),
    important(backgroundRepeat(noRepeat)),
    important(backgroundPosition(px(10), px(10))),
    important(backgroundSize(size(px(14), px(14)))),
    paddingLeft(px(inputSearchIconSize)),
  ],
);
global(".Select", [marginTop(px(3))]);

global(
  ".Select-placeholder, .Select-value",
  [important(marginLeft(px(inputSearchIconSize)))],
);

let popup = style([width(px(230)), minHeight(px(199))]);

Js.log(popup);

let selectButtonWrapper =
  style([
    border(px(1), solid, rgba(0, 0, 0, 0.2)),
    backgroundColor(white),
    paddingLeft(px(10)),
    borderRadius(px(3)),
    width(px(119)),
    height(px(26)),
    textAlign(`left),
    backgroundImage(url(dropdownArrowUrl)),
    backgroundPosition(px(119 - 20), px(10)),
    backgroundRepeat(noRepeat),
  ]);

let optionRowWrapper = style([minHeight(px(18)), display(inlineBlock)]);
let optionFlagIcon =
  style([width(px(14)), height(px(18)), marginRight(px(8))]);
