module Wrapper = (
  val NiceComponents.input(
        ~debugName="SearchWrapper",
        [|
          Raw("outline", "none"),
          Raw("border", "none"),
          Raw("box-sizing", "border-box"),
          BorderRadius(Px(3)),
          Display(Block),
          Width(Percent(100.)),
          Raw("box-shadow", "0 10px 40px 0 rgba(62,57,107,0.07), 0 2px 9px 0 rgba(62,57,107,0.06)"),
          Padding(Rem(1.)),
          MarginTop(Rem(1.)),
          Raw("font-size", "1rem"),
          Raw("transition", "0.25s"),
          Select(
            ":focus",
            [|Raw("box-shadow", "0 10px 40px 0 rgba(219,77,63,0.37), 0 2px\n9px 0 rgba(219,77,63,0.36);")|]
          )
        |]
      )
);

let component = ReasonReact.statelessComponent("Search");

let make = (~value="", ~onChange=_newValue => (), _children) => {
  ...component,
  render: _self =>
    <PageFrame> <Wrapper props={"value": value, "onChange": e => onChange(e##target##value)} /> </PageFrame>
};
