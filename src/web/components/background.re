open Nice;

let component = ReasonReact.statelessComponent("Background");

module Wrapper = (val NiceComponents.div(~name="Wrapper", [Raw("min-height", "100vh")]));

module Page = (
  val NiceComponents.div(~name="Page", [MaxWidth(Px(960)), Raw("margin", "auto")])
);

let make = (children) => {
  ...component,
  render: (_self) =>
    <Wrapper>
      <Page> (ReasonReact.createDomElement("div", ~props=Js.Obj.empty(), children)) </Page>
    </Wrapper>
};
