open Nice;

let component = ReasonReact.statelessComponent("");

let className = css([
  BackgroundColor(White),
  Raw("outline", "none"),
  BorderWidth(Px(0)),
  Padding(Px(0)),
  Width(Percent(100.)),
  Height(Em(1.5)),
  TextAlign(Center),
  Raw("font-size", "3rem"),
  MarginTop(Em(0.25))

]);

let make = (_children) => {
  ...component,
  render: (_self) => <input className />
};
