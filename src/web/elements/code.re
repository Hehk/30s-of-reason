open Utils;

module Wrapper = (
  val NiceComponents.code(
        ~debugName="Code",
        [|
          BackgroundColor(Hex("f8faff")),
          Display(Block),
          Padding(Rem(1.)),
          BorderRadius(Px(3))
        |]
      )
);
let component = ReasonReact.statelessComponent("Code");

let make = (~text, ~language="re", _children) => {
  ...component,
  render: (_self) => <Wrapper>
      (str_to_ele(text)) 
    </Wrapper>
};
