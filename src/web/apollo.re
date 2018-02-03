open ApolloInMemoryCache;

type dataObject = {
  .
  "__typename": string,
  "id": string,
  "key": string
};


/* Create an InMemoryCache */
let inMemoryCache = createInMemoryCache(~dataIdFromObject=(obj: dataObject) => obj##id, ());

/* Create an HTTP Link */
[@bs.module] external isNode : bool = "detect-node";
[@bs.module] external fetch : ApolloClient.fetch = "node-fetch";
let httpLink = if (isNode) {
  ApolloLinks.createHttpLink(~uri="/graphql", ~fetch, ());
} else {
  ApolloLinks.createHttpLink(~uri="/graphql", ());
};

module Client =
  ReasonApollo.CreateClient(
    {
      let apolloClient =
        ReasonApollo.createApolloClient(
          ~cache=inMemoryCache /* restore method can be piped e.g. inMemoryCache |> restore(window.__APOLLO__) */,
          ~link=httpLink,
          ()
        );
    }
  );
