open Nice;

let component = ReasonReact.statelessComponent("");

let outerCls = css([
  Raw("min-height", "100vh")
]);

let innerCls = css([
  MaxWidth(Px(960)),
  Raw("margin", "auto")
]);

let make = (children) => {
  ...component,
    render: (_self) => <div className=outerCls> 
      <div className=innerCls> (ReasonReact.createDomElement("div", ~props=Js.Obj.empty(), children))</div>
    </div>
};
