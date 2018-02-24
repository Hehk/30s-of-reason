open Utils;

/* Currently has to be done because the response type is internal to the Query module */
type response =
  | Loading
  | Loaded(Js.Json.t)
  | Failed(string);

let component = ReasonReact.statelessComponent("Query");

let make = (~query, ~render, _children) => {
  ...component,
  render: _self =>
    <Apollo.Context.Consumer>
      ...(
           client =>
             switch client {
             | None => ele_of_str("No Client")
             | Some(apolloQuery) =>
               module ReasonApolloQuery = (val apolloQuery);
               <ReasonApolloQuery query>
                 ...(
                      (response, parse) =>
                        switch response {
                        | Loading => render(Loading, parse)
                        | Loaded(x) => render(Loaded(x), parse)
                        | Failed(x) => render(Failed(x), parse)
                        }
                    )
               </ReasonApolloQuery>;
             }
         )
    </Apollo.Context.Consumer>
};
