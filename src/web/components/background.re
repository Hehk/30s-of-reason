open Nice;

let component = ReasonReact.statelessComponent("");

let outerCls = css([
  BackgroundColor(RGBa(219, 77, 63, 1.)),
]);

let innerCls = css([
  MaxWidth(Px(960)),
  Raw("margin", "auto")
]);

let make = (children) => {
  ...component,
    render: (_self) => <div className=outerCls> 
      <div className=innerCls> (ReasonReact.arrayToElement(children)) </div>
    </div>
};
