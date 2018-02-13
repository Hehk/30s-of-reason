open Theme;

include (
  val NiceComponents.div(
        ~debugName="Card",
        [|
          Raw("box-shadow", "0 10px 40px 0 rgba(62,57,107,0.07), 0 2px 9px 0 rgba(62,57,107,0.06)"),
          BackgroundColor(White),
          BorderRadius(Frame.borderRadius),
          Margin(Spacing.none),
          MarginTop(Spacing.normal),
          MarginBottom(Spacing.normal),
          Padding(Spacing.normal),
          PaddingBottom(Px(1))
        |]
      )
);
