open Utils;

module Wrapper = (
  val NiceComponents.code(
        ~debugName="Code",
        [|
          Display(Block),
          Padding(Rem(1.)),
          BorderRadius(Px(3)),
          MarginBottom(Rem(1.)),
          BackgroundColor(Hex("282C34")),
          Color(Hex("ABB2BF")),
          Raw("box-shadow", "0 10px 40px 0 rgba(62,57,107,0.07), 0 2px 9px 0 rgba(62,57,107,0.06)"),
          Raw("font-size", "1rem"),
          LineHeight(1.5)
        |]
      )
);

module Line = (val NiceComponents.div(~debugName="Line", [|Raw("white-space", "pre")|]));

module LineNumber = (
  val NiceComponents.span(
        ~debugName="LineNumber",
        [|MinWidth(Rem(2.)), Display(InlineBlock), Raw("user-select", "none"), Color(Hex("5C6370"))|]
      )
);

module Language = (
  val NiceComponents.span(
    ~debugName="Language",
    [|Raw("float", "right"), Color(Hex("db4d3f"))|]
    )
);

let component = ReasonReact.statelessComponent("Code");

let make = (~text, ~language="re", _children) => {
  ...component,
  render: _self =>
    <Wrapper>
      <Language>(ele_of_str(language))</Language>
      (
        ele_of_arr(
          text
          |> Js.String.split("\n")
          |> Array.mapi((i, line) =>
               <Line key=(string_of_int(i))>
                 <LineNumber> (ele_of_str(string_of_int(i))) </LineNumber>
                 (ele_of_str(line))
               </Line>
             )
        )
      )
    </Wrapper>
};
