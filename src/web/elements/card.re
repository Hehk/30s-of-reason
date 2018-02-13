open Theme;

include (
  val NiceComponents.div(
        ~debugName="Card",
        [|
          Raw("box-shadow", Frame.Shadow.normal),
          BackgroundColor(White),
          BorderRadius(Frame.borderRadius),
          Margin(Spacing.none),
          MarginTop(Spacing.normal),
          MarginBottom(Spacing.normal),
          Padding(Spacing.normal),
          PaddingBottom(Px(1)),
        |]
      )
);
